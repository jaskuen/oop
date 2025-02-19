set PROGRAM="%~1"

rem При неправильном количестве параметров ожидается ошибка (1)
%PROGRAM% in.txt > nul && goto err
echo Test 1 passed

rem При неправильном количестве параметров ожидается ошибка (3)
%PROGRAM% in.txt out.txt a.txt && goto err
echo Test 2 passed

rem Умножение на единичную матрицу
%PROGRAM% edMatr.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" edMatr_ans.txt >nul || goto err
echo Test 3 passed

rem Умножение на нулевую матрицу
%PROGRAM% zeroMatr.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" zeroMatr_ans.txt >nul || goto err
echo Test 4 passed

rem Менее трех чисел в строке матрицы
%PROGRAM% twoNums.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" error.txt >nul || goto err
echo Test 5 passed

rem Нет последней строки в матрице(упал на контесте)
%PROGRAM% noLastLine.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" error.txt >nul || goto err
echo Test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1