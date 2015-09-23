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
	
	NSString* appid=@"07122dfe-3916-981b-cd4e-b55c4e03892f";
	NSString* sid=@"18a2b988-06d5-44cc-9d19-29617ad0d5ce";
	
	Mutyda* mutyda=[[Mutyda alloc] init];
	[mutyda autenticationWithSID:sid appID:appid appScheme:appScheme appURL:appUrl];
}
 
@end
```

В качестве параметров вы должны передать URL и идентификатор схемы, которые вы определили в вашем plist файле. Значение **appid** вы должны указать то, которое сгенерировалось, когда вы создавали сценарий **(это ID сценария)** в вашем личном кабинете партнера на сайте Mutyda.com
Значение **sid** - это своего рода идентификатор сессии. В качестве значения вы можете использовать любую сгенерированную вами случайную строку. Например это может быть сгенерированный GUID. Если вы при вызове метода autenticationWithSID каждый раз подаете разное значение **SID**, то mutyda сервис всегда будет начинать процесс авторизации с начала. Если вы уже прошли один раз авторизовались и в течении 10-и минут пытаетесь авторизоваться снова, причем значение sid вы передаете такое же как и первый раз, в этом случае mutyda сервис вас авторизует автоматически (таймаут сессии на сервере Mutyda равен 10-и минутам)


Готовый пример демонстрирующий авторизацию с помощью сервиса Mutyda вы можете загрузить с GitHub по адресу 
[https://github.com/mutyda/mutyda-auth-ios-example][example]**
[example]: https://github.com/mutyda/mutyda-auth-ios-example


## License

The MIT license (Refer to the [LICENSE.md][license] file)

[license]: https://github.com/mutyda/ios-static-library/blob/master/LICENSE.md

