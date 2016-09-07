sc create "FoveRuntime" binPath="%~dp0FoveServiceHost.exe"
sc sdset FoveRuntime D:(A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)(A;;RPWP;;;WD)
pause