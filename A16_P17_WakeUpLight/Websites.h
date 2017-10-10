
//Converted with http://www.percederberg.net/tools/text_converter.html to C-String Text and saved as char

const char index[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=2.0, user-scalable=yes\">\n<tilte><h1>NanoESP WakeUp Light</h1></tilte>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\">\n<HR>\nSet up your WakeUp Timer\n<BR><BR>\n\n<form action=\"/settimer\">\n<table>\n\t<tr><td>Time: </td><td><input type=\"time\" name=\"timer\"></td></tr>\n\t<tr><td>Duration:</td><td><input type=\"number\" name=\"duration\" min=\"1\" max=\"60\" step=\"1\" value=\"30\"> min</td></tr>\n\t<tr></tr>\n\t<tr><td></td><td><input type=\"submit\" onclick=\"return sendForm(this.form);\"></td></tr>\n</table>\n</form>\n<form action=\"/turnoff\">\n\t<button type=\"submit\" name=\"led\" value=\"0\" onclick=\"return sendForm(this.form);\">Turn LED OFF</button>\n</form>\n<HR>\n<script language=\"JavaScript\">\nfunction sendForm(form) {\n  var formData =\"\";\n  \tfor (var i = 0, d, v; i < form.elements.length; i++) {\n\t\td = form.elements[i];\n\t\tif (d.name && d.value) {\n\t\t\tv = (d.type == \"checkbox\" || d.type == \"radio\" ? (d.checked ? d.value : \"\") : d.value);\n\t\t\tif (v) formData += d.name + \"=\" + escape(v) + \"&\";\n\t\t}\n\t}\n  var xhr = new XMLHttpRequest();\n  xhr.open('POST', form.action, true);\n  xhr.send(formData);\n  return false;\n}\n\n</script>\n\n</BODY>\n</HTML>\0"
};

const char error404[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"> \n<title>\nError\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>Error 404: File or Page not found</h1>\n<HR><BR>\n<a href=\"/\">Main Page</a><br>\n<br>\n<br>\n<HR><BR>\n</body>\n</HTML>\0"
};


