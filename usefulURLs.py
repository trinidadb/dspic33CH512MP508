#RUN ON ANACOND PROMPT "C:\Users\Trini\Downloads>cmd /s /c python usefulURLs.py"
# replace "C:\Users\Trini\Downloads" with the folder in which the file is located
import webbrowser
import os


url1 = "https://microchipdeveloper.com/16bit:ch-example"
url2 = "https://microchipdeveloper.com/mcc:overview"
url3 = "https://microchipdeveloper.com/mcc:mplab-code-configurator-support-for-dual-core-devices"
url4 = "file://"+os.getcwd()+'/'"file.html"
url5 = "https://www.microchip.com/en-us/product/dsPIC33CH512MP508"
url6 = "https://ww1.microchip.com/downloads/en/Appnotes/AN2721,-Getting-Started-with-Dual-Core-DS00002721A.pdf"
url7 = "https://microchipsupport.force.com/s/article/Code-example--Dual-Core-dsPIC33CH---MSI-communication"
url8 = "https://groups.io/g/EdenDSP/topic/78786953#1483"
url9 = "file://"+os.getcwd()+'/'"whenRunningDemo.html"
url10 = "https://microchip.wikidot.com/16bit:osc-posc"
url11 = "https://www.youtube.com/watch?v=54cX8s8SREg"
url12 = "https://onlinedocs.microchip.com/pr/GUID-70ACD6B0-A33F-4653-B192-8465EAD1FD98-en-US-5/index.html?GUID-9E83B3BE-18B2-4990-AD52-2FB6969B0D6F"


urls = [url1,url2,url3,url4,url5,url6,url7,url8,url9,url10,url11,url12]

first = True
for url in urls:
	if first:
		webbrowser.open(url1,new=1)
		first = False
	else:
		webbrowser.open(url)