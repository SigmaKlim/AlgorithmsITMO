# AlgorithmsITMO
Данный проект реализует игру "Великий правитель Египта".
При запуске пользователя встречает главное меню игры. Пункты меню: загрузить игру с сохранения, начать новую игру, ознакомиться с правилами и выйти.
Навигация по игре осуществляется цифровыми клавишами. 
В начале игры пользователь задает название городу, по после чего генерируется, собственно, город (структура city с полями name, area, population, wheat и 
accumStarvedToDeath). На экран выводятся статы города (значения его полей). Далее, согласно правилам, каждый ход игрок может отдавать приказы (продать 
землю, купить землю, роздать зерно на пищу горожанам и засеять поля пшеницей). При этом отображается соответствующее меню. При этом, пользователь может
менять и отдавать новые приказы путем навигации по меню до тех пор пока в нем не будет выбрана команда Finish. Числовые показатели, которые вводит пользователь
вносятся в поля структы input. Удобно, что пользователь видит на экране, какие приказы он уже отдал. Кроме того, контролируется, чтобы введенные значения не
выходили за допустимые ограничения. После завершения ввода приказов в поля структуры turn вносятся рассчитанные значения хода (умершие от голода,
урожай зерна и т. д.), а также обновляются статы города. Затем, в начале каждого хода выводится информация о прошедшем годе. 
Кроме того, есть опция выйти из игры с сохранением.  При этом в файл сохранения записываются все статы города и данные последнего сделанного хода.
При последующей загрузке в поля структуры turn заносятся значения из сейв-файла и игра запускается с начала последующего хода.
Если игрок не проиграл в течение 10 ходов, по истечении их выводит статистику партии и оценку игрока.

Пример вывода в консоль в начале хода:
CITY: Innsmouth         POPULATION: 116 AREA: 1480      WHEAT: 9251

My Lord, allow me to inform you about the news in our great capital Innsmouth.

It is year 5 of your blessed reign.
16 people have arrived to Innsmouth.
Our farmers harvested 4 bushels of wheat from an acre making the total harvest equal 4000
Today I was told that disgusting rats devoured 718 bushels of our finest wheat. What a misery!
Each acre of land costs 28 bushels.

My lord, I am listening to your orders!
        1. Purchase some land.
        2. Sell some land
        3. Let citizens have some wheat for food.
        4. Sow some land with wheat.
        5. Finish
        0. Quit the game

Choose the command by pressing the number + ENTER. Previous order will be revoked.

Your active orders:
        Land to purchase: 0 acres.
        Land to sell: 0 acres.
        Wheat for food: 0 bushels.
        Land to sow: 0 acres.
