set PROGRAM="%~1"

rem Тест 1: запуск без параметров
%PROGRAM% > nul && goto err

echo Test 1 passed

rem Тест 2: неправильное название файла
%PROGRAM% foxxxx.txt "%TEMP%\fox.txt" bird cat || goto err

echo Test 2 passed

rem Тест 3: исходная строка отсутствует в файле
%PROGRAM% fox.txt "%TEMP%\fox.txt" bird cat || goto err
fc.exe "%TEMP%\fox.txt" fox.txt >nul || goto err

echo Test 3 passed

rem Тест 4: исходная строка присутсвует в файле
%PROGRAM% fox.txt "%TEMP%\fox.txt" dog cat || goto err
fc.exe "%TEMP%\fox.txt" fox-replace-dog-with-cat.txt >nul || goto err

echo Test 4 passed

rem Тест 5: предложенный тест при вложенности строк
%PROGRAM% numbers.txt "%TEMP%\numbers.txt" 1231234 numbers || goto err
fc.exe "%TEMP%\numbers.txt" numbers-expected-return.txt >nul || goto err

echo Test 5 passed

rem Тест 6: исходная строка - пустая
%PROGRAM% numbers.txt "%TEMP%\numbers.txt" "" numbers || goto err
fc.exe "%TEMP%\numbers.txt" numbers.txt >nul || goto err

echo Test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1