set PROGRAM="%~1"

rem При отсутствии параметров ожидается ненулевой выход
%PROGRAM% > nul && goto err
echo Test 1 passed

rem Ожидается ошибка открытия файла
%PROGRAM% matttrix.txt || goto err
echo Test 2 passed

rem Ожидается ошибка неправильной матрицы (не квадратная)
%PROGRAM% matrixNotSquare.txt || goto err
echo Test 3 passed

%PROGRAM% matrix1.txt > "%TEMP%\matrix1inv.txt" || goto err
fc.exe "%TEMP%\matrix1inv.txt" matrix1inv.txt >nul || goto err
echo Test 4 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1