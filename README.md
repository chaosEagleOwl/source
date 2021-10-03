# source
Расчетный модуль по расчету несущих конструкций зданий и сооружений с открытым исходным кодом

Для работы с проектом нужна среда разработки Visual Studio и установленный Autocad.
До начала работы с проектом Вам следует определиться в какой версии Autocad вы будете работать и установить для этого соотвествующую версию Visaul Studio и библиотеки Objectarx.

Ссылки на библиотеки ObjectArx приведены здесь:
https://adn-cis.org/forum/index.php?topic=61.0


Соответствие между версиями Visual Studio и Autocad приведено в файле, который находится в корне репозитория рядом с файлом README.md 
\Версии Visual Studio.rtf

Проект предполагает возможность работы с различными версиями Visual Studio, поэтому для каждой версии Visual Studio создан свой каталог.

Пути к библиотекам в проектах на Visual Studio прописываются следубщим образом.
Расположение библиотек ObjectArx после скачивания и распаковки предполагается на диске C:

для Visual Studio 2012 и Acad 2016
C:\ArxLib\Autodesk_ObjectARX_2016_Win_64_and_32_Bit\

для Visual Studio 2015 и Acad 2018
C:\ArxLib\Autodesk_ObjectARX_2018_Win_64_and_32_Bit\

для Visual Studio 2017 и Acad 2020
C:\ArxLib\Autodesk_ObjectARX_2020_Win_64_and_32_Bit\

для Visual Studio 2018 и Acad 2019
C:\ArxLib\ObjectARX_for_AutoCAD_2020_Win_64_bit\

для Visual Studio 2021 и Acad 2021
C:\ArxLib\ObjectARX_for_AutoCAD_2021_Win_64bit_dlm\


Для исключения конфликта путей расположение репозитория GitHub предполагается на диске C:\

Таким образом, путь к файлу README.md у каждого пользователя после синхронизации с GitHub должен быть:
C:\GitHub\source\README.md

Имеются папки:

C:\GitHub\source\Common\ - папка для основного исходного кода, которые разарбатывается совместно. 
                          Эта папка является общей для всех версий Visual Studio (поддерживаемых)

C:\GitHub\source\VS2012(c++)ac2016\ - папка с проектом для Visual Studio 2012 и Acad 2016

C:\GitHub\source\VS2015(c++)ac2018\ - папка с проектом для Visual Studio 2015 и Acad 2018

C:\GitHub\source\VS2017(c++)ac2020\ - папка с проектом для Visual Studio 2017 и Acad 2020

C:\GitHub\source\VS2019(c++)ac2021\ - папка с проектом для Visual Studio 2021 и Acad 2021


Для тестирования пока реализована только команда (из командной строки) -
MYHELLO
которая приветствует мир.


Для отладки в Autocad при помощи команды (через командную строку) _appload
в список автозагрузки должен быть загружен файл:

для Autocad 2016:
C:\GitHub\source\VS2012(c++)ac2016\ArxProject1\x64\Debug\ArxProject1.arx

для Autocad 2018:
C:\GitHub\source\VS2015(c++)ac2018\ArxProject1\x64\Debug\ArxProject1.arx

для Autocad 2020:
C:\GitHub\source\VS2017(c++)ac2020\ArxProject1\x64\Debug\ArxProject1.arx

для Autocad 2021:
C:\GitHub\source\VS2019(c++)ac2021\ArxProject1\x64\Debug\ArxProject1.arx