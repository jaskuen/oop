set PROGRAM="%~1"

rem При отсутствии параметров ожидается ненулевой выход
%PROGRAM% > nul && goto err
echo Test 1 passed

rem Ожидается получение ошибки введения неправильного символа для степени исходной системы счисления
%PROGRAM% -n 35 10 || goto err

echo Test 2 passed

rem Ожидается получение ошибки введения неправильного символа для степени результативной системы счисления
%PROGRAM% 2 !! 0 || goto err

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

echo OK
exit 0

:err
echo Program testing failed
exit 1