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

Выберите закладку “Build Phases”,  раскройте пункт “Link Binary Libraries” и нажмите кнопку +

![build.gradle](https://mutyda.com/images/for-git/a5.png "build.gradle")

В появившемся окне нажмие кнопку “Add Other” и выбирите библиотеку libMutyda.a, которая находится в папке Lib вашего проекта.

![build.gradle](https://mutyda.com/images/for-git/a6.png "build.gradle")

В результате у вас должно получиться следущее

![build.gradle](https://mutyda.com/images/for-git/a7.png "build.gradle")

Перейдите на закладку “Build Settings” и отфильтруйте настройки по фразе “other linker”

![build.gradle](https://mutyda.com/images/for-git/a8.png "build.gradle")

Добавьте параметр -ObjC ка показано на рисунке

![build.gradle](https://mutyda.com/images/for-git/a9.png "build.gradle")


## License

The MIT license (Refer to the [LICENSE.md][license] file)

[license]: https://github.com/mutyda/ios-static-library/blob/master/LICENSE.md

