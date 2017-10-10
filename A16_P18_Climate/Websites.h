
//Converted with http://www.percederberg.net/tools/text_converter.html to C-String Text and saved as char

const char index[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=2.0, user-scalable=yes\">\n<tilte><h1>NanoESP CLimate</h1></tilte>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\">\n<HR>\nCurrent climate values from NanoESP:\n<BR><BR>\n\nTempertur:<BR>\n<meter id=\"temp\" name=\"temp\" min = \"-20\" max=\"60\" value=\"0\"></meter><output id=\"otemp\"></output><BR>\nHumidity:<BR>\n<meter id=\"hum\" name=\"hum\" min=\"0\" max=\"100\" value=\"0\"></meter><output id=\"ohum\"></output><BR>\nLight:<BR>\n<meter id=\"light\" name=\"light\" max=\"1023\" value=\"0\"></meter><output id=\"olight\"></output><BR>\n\n<HR>\n</font>\n<textarea id=\"msg\" name=\"message\" rows=\"5\" cols=\"40\">\n\n</textarea>\n\n<script language=\"JavaScript\">\nvar source = new EventSource(\"/eventclimate\");\n\nsource.addEventListener('temp', function(e) {\n  document.getElementById(\"temp\").value = e.data;\n  document.getElementById(\"otemp\").value = e.data +\" C\";\n}, false);\n\nsource.addEventListener('light', function(e) {\n  document.getElementById(\"light\").value = e.data;\n  document.getElementById(\"olight\").value = e.data;\n}, false);\nsource.addEventListener('hum', function(e) {\n  document.getElementById(\"hum\").value = e.data;\n  document.getElementById(\"ohum\").value = e.data+\" %\";\n}, false);\n\n\nsource.addEventListener('msg', function(e) {\n\tdocument.getElementById('msg').value += e.data;\n}, false);\n</script>\n\n</BODY>\n</HTML>\0"
};

const char error404[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"> \n<title>\nError\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>Error 404: File or Page not found</h1>\n<HR><BR>\n<a href=\"/\">Main Page</a><br>\n<br>\n<br>\n<HR><BR>\n</body>\n</HTML>\0"
};


