set PROGRAM="%~1"

rem При неправильном количестве параметров ошибка (1)
%PROGRAM% in.txt > nul && goto err
echo Test 1 passed

rem При неправильном количестве параметров ошибка (3)
%PROGRAM% in.txt out.txt a.txt && goto err
echo Test 2 passed

rem Ошибка открытия файла для чтения
%PROGRAM% innn output1.txt && goto err
echo Test 3 passed

rem Заполнение замкнутой области
%PROGRAM% input1.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output1.txt >nul || goto err
echo Test 4 passed

rem Заполнение открытой области
%PROGRAM% input2.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output2.txt >nul || goto err
echo Test 5 passed

rem Заполнение нескольких областей, между ними пустые строки
%PROGRAM% input3.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output3.txt >nul || goto err

echo Test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1