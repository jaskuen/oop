set PROGRAM "%~1"

rem ��������� ������� ������ ����� � ������ �����
%PROGRAM% empty.txt %TEMP%/empty.txt string anotherString
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1