set PROGRAM="%~1"

rem ���� 1: ������ ��� ����������
%PROGRAM% > nul && goto err

echo Test 1 passed

rem ���� 2: ������������ �������� �����
%PROGRAM% foxxxx.txt "%TEMP%\fox.txt" bird cat || goto err

echo Test 2 passed

rem ���� 3: �������� ������ ����������� � �����
%PROGRAM% fox.txt "%TEMP%\fox.txt" bird cat || goto err
fc.exe "%TEMP%\fox.txt" fox.txt >nul || goto err

echo Test 3 passed

rem ���� 4: �������� ������ ����������� � �����
%PROGRAM% fox.txt "%TEMP%\fox.txt" dog cat || goto err
fc.exe "%TEMP%\fox.txt" fox-replace-dog-with-cat.txt >nul || goto err

echo Test 4 passed

rem ���� 5: ������������ ���� ��� ����������� �����
%PROGRAM% numbers.txt "%TEMP%\numbers.txt" 1231234 numbers || goto err
fc.exe "%TEMP%\numbers.txt" numbers-expected-return.txt >nul || goto err

echo Test 5 passed

rem ���� 6: �������� ������ - ������
%PROGRAM% numbers.txt "%TEMP%\numbers.txt" "" numbers || goto err
fc.exe "%TEMP%\numbers.txt" numbers.txt >nul || goto err

echo Test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1