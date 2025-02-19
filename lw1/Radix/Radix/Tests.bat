set PROGRAM="%~1"

rem При отсутствии параметров ожидается ненулевой выход
%PROGRAM% > nul && goto err
echo Test 1 passed

rem Ожидается получение ошибки введения неправильного символа для степени исходной системы счисления
%PROGRAM% -n 35 10 && goto err

echo Test 2 passed

rem Ожидается получение ошибки введения неправильного символа для степени результативной системы счисления
%PROGRAM% 2 !! 0 && goto err

echo Test 3 passed

rem Проверка перевода положительного числа
%PROGRAM% 10 16 256 > "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" 1016256.txt >nul || goto err

echo Test 4 passed

rem Проверка перевода отрицательного числа
%PROGRAM% 10 16 -256 > "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" -1016256.txt >nul || goto err

echo Test 5 passed

rem Проверка на MAX_INT
%PROGRAM% 36 10 ZIK0ZJ > "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" INT_MAX.txt >nul || goto err

echo Test 6 passed

rem Проверка на MIN_INT
%PROGRAM% 36 10 -ZIK0ZK > "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" INT_MIN.txt >nul || goto err

echo Test 7 passed

rem Проверка на MAX_INT + 1
%PROGRAM% 36 10 ZIK0ZK > "out.txt" && goto err
echo Test 8 passed

rem Проверка на MIN_INT - 1
%PROGRAM% 36 10 -ZIK0ZL > "out.txt" && goto err
echo Test 9 passed

rem Исходная система счисления вне диапазона
%PROGRAM% -1 10 10 > "out.txt" && goto err
echo Test 10 passed

rem Проверка на MIN_INT - 1
%PROGRAM% 10 -10 10 > "out.txt" && goto err
echo Test 11 passed

rem MAX_INT + 1, MIN_INT - 1, системы счисления вне диапазона

echo OK
exit 0

:err
echo Program testing failed
exit 1