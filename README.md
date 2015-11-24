# Mutyda iOS Library
**Эта библиотека предназнача для получения авторизации на то или иное действие в вашем iOS приложении посредством сервиса [https://mutyda.com][mutydasite]**
[mutydasite]: https://mutyda.com

Подготовка к использованию данной библиотеки
----------
Прежде чем использовать данную библиотеку вам необходимо зайти в личный кабинет партнера на сайте  **[mutyda.com](https://mutyda.com/pcabinet.aspx)** и создать новый сценарий указав в поле “Тип сценария” значение “Авторизация в iOS приложении”. Когда вы создадите новый сценарий запомните значение "ID сценария", оно вам понадобится в дальнейшем

Добавление статической библиотеки в ваш Xcode проект
-----------
Распакуйте скаченный архив библиотеки в корнеувю папку вашего проекта.
У вас получится следующая структура папок

![build.gradle](https://mutyda.com/images/for-git/a3.png "build.gradle")

В навигаторе проектов выберите ваш проект, затем вашу цель и на вкладке BuildSettings в окне поиска наберите  “header search” для фильтрации списка настроек

![build.gradle](https://mutyda.com/images/for-git/a4.png "build.gradle")

Раскройте пункт Header Search Paths и дважды кликните на пункте Debug. В появившемся всплыващем окне нажмите кнопку + и добавите значение $SOURCE_ROOT/include

![build.gradle](https://mutyda.com/images/for-git/a5.png "build.gradle")

Выберите закладку “Build Phases”,  раскройте пункт “Link Binary Libraries” и нажмите кнопку +

![build.gradle](https://mutyda.com/images/for-git/a6.png "build.gradle")

В появившемся окне нажмие кнопку “Add Other” и выбирите библиотеку libMutyda.a, которая находится в папке Lib вашего проекта.

![build.gradle](https://mutyda.com/images/for-git/a7.png "build.gradle")

В результате у вас должно получиться следущее

![build.gradle](https://mutyda.com/images/for-git/a8.png "build.gradle")

Перейдите на закладку “Build Settings” и отфильтруйте настройки по фразе “other linker”

![build.gradle](https://mutyda.com/images/for-git/a9.png "build.gradle")

Добавьте параметр -ObjC ка показано на рисунке

![build.gradle](https://mutyda.com/images/for-git/a9_2.png "build.gradle")

**Использование библиотеки в вашем проекте**

Для использования библиотеки в вашем проекте вам необходимо сначала добавить пользовательскую схему в ваш проект. Для этого в plist файле вашего проекта добавьте вашу схему.

![build.gradle](https://mutyda.com/images/for-git/a10.png "build.gradle")

подключите заголовочный файл ```#import “Mutyda.h”``` и в том месте, где необходимо авторизоваться посредством сервиса Mutyda просто вызовите метод autenticationWithSID у созданного экземпляра класса Mutyda

```Objective-C
- (IBAction)MutydaClick:(id)sender {
	
	NSString* appUrl=@"mutyda.com";
	NSString* appScheme=@"auth";
	
	NSString* appid=@"id_вашего_сценария_из_личного_кабинете";
	NSString* sid=@"случайным_образом_сгенерированная_строка";
	
	Mutyda* mutyda=[[Mutyda alloc] init];
	[mutyda autenticationWithSID:sid appID:appid appScheme:appScheme appURL:appUrl];
}
 
@end
```

В качестве параметров вы должны передать URL и идентификатор схемы, которые вы определили в вашем plist файле. Значение **appid** вы должны указать то, которое сгенерировалось, когда вы создавали сценарий **(это ID сценария)** в вашем личном кабинете партнера на сайте Mutyda.com
Значение **sid** - это своего рода идентификатор сессии. В качестве значения вы можете использовать любую сгенерированную вами случайную строку. Например это может быть сгенерированный GUID. Если вы при вызове метода autenticationWithSID каждый раз подаете разное значение *sid**, то mutyda сервис всегда будет начинать процесс авторизации с начала. Если вы уже прошли один раз авторизовались и в течении 10-и минут пытаетесь авторизоваться снова, причем значение sid вы передаете такое же как и первый раз, в этом случае mutyda сервис вас авторизует автоматически (таймаут сессии на сервере Mutyda равен 10-и минутам)

После вызова метода autenticationWithSID экземпляра класса Mutyda управление будет передано мобильному браузеру, который перенаправит вас на сайт https://mutyda.com и предолжит пройти процесс аутентификации инициатора запроса и будет ждать когда пользователь получит авторизацию на действие описанное в сценарии в личном кабинете.

В не зависимости от того, успешно или нет авторизовался инициатор запроса браузер перенаправит пользователя обратно в приложение и вы должны обязательно в методе 

**- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation**
  
вашего делегата приложения осуществить проверку данных, которые вернул браузер. Для этого вам необходимо вызвать метод **checkAuthenticationResultFromURL** экземпляра класса Mutyda, который вернет строковое представление JSON объекта с данными о лидере группы. Если результат выполнения данного метода пустой, то эо значит, что авторизация на совершение действия согласно сценария не получена.


```Objective-C
@implementation MSAppDelegate

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    Mutyda* m=[[Mutyda alloc] init];
    NSString* jsonMutydaData=[m checkAuthenticationResultFromURL:url];

    if ([jsonMutydaData length]!=0)
    {
        NSLog(@"JSON string from Mutyda service: %@",jsonMutydaData);
    }
        NSLog(@"Authorization failed");

    return YES;
}
```

Имена полей этого JSON объекта с данными о лидере группы могут добавляться, на данный момент это следующие поля

JSON свойство | Назначение |
--- | --- |
first_name | Имя лидера группы |
last_name | Фамилиия лидера группы |
second_name | Отчество лидера группы |
user_id|ID лидера группы в системе Mutyda  |
phone|Телефон лидера группы  |
token|авторизационный токен (вам не понадобиться его использовать где либо)  |
email|Емайл лидера группы  |
status|Статус авторизации (true все в порядке, fase запрет авторизации)  |
user_decline|используется только в методе error показываем имя пользователя из группы, кто запретил авторизацию  |

Готовый пример демонстрирующий авторизацию с помощью сервиса Mutyda вы можете загрузить с GitHub по адресу 
[https://github.com/mutyda/mutyda-auth-ios-example][example]
[example]: https://github.com/mutyda/mutyda-auth-ios-example


## License

The MIT license (Refer to the [LICENSE.md][license] file)

[license]: https://github.com/mutyda/ios-static-library/blob/master/LICENSE.md

