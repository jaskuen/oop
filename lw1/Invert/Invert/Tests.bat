set PROGRAM="%~1"

rem ��� ���������� ���������� ��������� ��������� �����
%PROGRAM% > nul && goto err
echo Test 1 passed

rem ��������� ������ �������� �����
%PROGRAM% matttrix.txt || goto err
echo Test 2 passed

rem ��������� ������ ������������ ������� (�� ����������)
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