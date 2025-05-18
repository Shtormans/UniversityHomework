@echo off
chcp 65001 > nul

set base_path="D:\Desktop\PracticWork\University\АК\LR_3\Лабораторні\ПЗ-24у-1\Кондрачук Олександр Вадимович\batch"
set visible=%base_path%"\Неприхована папка"
set hidden=%base_path%"\Прихована папка"

if not exist %visible% (
    mkdir %visible%
)

if not exist %hidden% (
    mkdir %hidden%
)

attrib +h %hidden%

xcopy /? > %visible%\copyhelp.txt
xcopy %visible%\copyhelp.txt %hidden%\copied_copyhelp.txt*

pause