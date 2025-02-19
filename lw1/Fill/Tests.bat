set PROGRAM="%~1"

rem ��� ������������ ���������� ���������� ������ (1)
%PROGRAM% in.txt > nul && goto err
echo Test 1 passed

rem ��� ������������ ���������� ���������� ������ (3)
%PROGRAM% in.txt out.txt a.txt && goto err
echo Test 2 passed

rem ������ �������� ����� ��� ������
%PROGRAM% innn output1.txt && goto err
echo Test 3 passed

rem ���������� ��������� �������
%PROGRAM% input1.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output1.txt >nul || goto err
echo Test 4 passed

rem ���������� �������� �������
%PROGRAM% input2.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output2.txt >nul || goto err
echo Test 5 passed

rem ���������� ���������� ��������, ����� ���� ������ ������
%PROGRAM% input3.txt "%TEMP%\out.txt" || goto err
fc.exe "%TEMP%\out.txt" output3.txt >nul || goto err

echo Test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1