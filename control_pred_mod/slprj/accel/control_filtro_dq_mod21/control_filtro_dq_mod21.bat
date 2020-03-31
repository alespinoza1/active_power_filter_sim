@echo off
set MATLAB=C:\Program Files\MATLAB\R2017b
"%MATLAB%\bin\win64\gmake" -f control_filtro_dq_mod21.mk  ISPROTECTINGMODEL=NOTPROTECTING
