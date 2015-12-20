//
//  HTML PAGE
//
const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
<!doctype html>
<meta name="viewport" content="width=device-width, initial-scale=1" />
<script>function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url)
{
	microAjax(url, function (res)
	{
		res.split(String.fromCharCode(10)).forEach(function(entry) {
		fields = entry.split("|");
		if(fields[2] == "input")
		{
				document.getElementById(fields[0]).value = fields[1];
		}
		else if(fields[2] == "div")
		{
				document.getElementById(fields[0]).innerHTML  = fields[1];
		}
		else if(fields[2] == "chk")
		{
				document.getElementById(fields[0]).checked  = fields[1];
		}
	  });
	});
}</script> 
<html>
	<head>
	<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title></title>
	<meta charset="utf-8" />
	<style>.btn,.btn:link,.btn:visited,body{font-family:avenir,helvetica,arial,sans-serif;letter-spacing:.15em}body{color:#000}hr{background-color:#eee;border:0;color:#eee;height:1px}.btn,.btn:link,.btn:visited{border-radius:.3em;border-style:solid;border-width:1px;color:#111;display:inline-block;margin-bottom:.5em;padding:1em .75em;text-decoration:none;text-transform:uppercase;-webkit-transition:color .4s,background-color .4s,border .4s;transition:color .4s,background-color .4s,border .4s}.btn:focus,.btn:hover{color:#7FDBFF;border:1px solid #7FDBFF;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn:active{color:#0074D9;border:1px solid #0074D9;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn--s{font-size:12px}.btn--m{font-size:14px}.btn--l{font-size:20px;border-radius:.25em!important}.btn--full,.btn--full:link{border-radius:.25em;display:block;margin-left:auto;margin-right:auto;text-align:center;width:100%}.btn--blue:link,.btn--blue:visited{color:#fff;background-color:#0074D9}.btn--blue:focus,.btn--blue:hover{color:#fff!important;background-color:#0063aa;border-color:#0063aa}.btn--blue:active{color:#fff;background-color:#001F3F;border-color:#001F3F}@media screen and (min-width:32em){.btn--full{max-width:16em!important}}
	</style>
	</head>
	<body>
<h1 style="font-family:Helvetica Neue, Helvetica, Arial, SANS-SERIF;font-size:3em; margin:.5em;font-weight:100;">Mitchine</h1>
<a href="admin.html"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Network Configuration</strong>
<hr>
Connect to Router with these settings:<br>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
<tr><td align="right">SSID:</td><td><input type="text" id="ssid" name="ssid" value=""></td></tr>
<tr><td align="right">Password:</td><td><input type="text" id="password" name="password" value=""></td></tr>
<tr><td align="right">DHCP:</td><td><input type="checkbox" id="dhcp" name="dhcp"></td></tr>
<tr><td align="right">IP:     </td><td><input type="text" id="ip_0" name="ip_0" size="3">.<input type="text" id="ip_1" name="ip_1" size="3">.<input type="text" id="ip_2" name="ip_2" size="3">.<input type="text" id="ip_3" name="ip_3" value="" size="3"></td></tr>
<tr><td align="right">Netmask:</td><td><input type="text" id="nm_0" name="nm_0" size="3">.<input type="text" id="nm_1" name="nm_1" size="3">.<input type="text" id="nm_2" name="nm_2" size="3">.<input type="text" id="nm_3" name="nm_3" size="3"></td></tr>
<tr><td align="right">Gateway:</td><td><input type="text" id="gw_0" name="gw_0" size="3">.<input type="text" id="gw_1" name="gw_1" size="3">.<input type="text" id="gw_2" name="gw_2" size="3">.<input type="text" id="gw_3" name="gw_3" size="3"></td></tr>

<tr><td align="right">MQTT Server</td><td><input type="text" id="mqttServer" name="mqttServer" value=""></td></tr>
<tr><td align="right">Device Identifier</td><td><input type="text" id="deviceIdentifier" name="deviceIdentifier" value=""></td></tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<hr>
<strong>Connection State:</strong><div id="connectionstate">N/A</div>
<hr>
<strong>Networks:</strong><br>
<table border="0"  cellspacing="3" style="width:310px" >
<tr><td><div id="networks">Scanning...</div></td></tr>
<tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="btn btn--m btn--blue">Refresh</a></td></tr>
</table>


<script>

function GetState()
{
	setValues("/admin/connectionstate");
}
function selssid(value)
{
	document.getElementById("ssid").value = value; 
}

window.onload = function ()
{

					setValues("/admin/values");
					setTimeout(GetState,3000);

}



</script>
</body>
</html>


)=====";

const char PAGE_WaitAndReload[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=config.html">
Please Wait....Configuring and Restarting.
)=====";


//
//  SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
// 

void send_network_configuration_html()
{
	
	if (server.args() > 0 )  // Save Settings
	{
		String temp = "";
		config.dhcp = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "ssid") config.ssid =   urldecode(server.arg(i));
			if (server.argName(i) == "password") config.password =    urldecode(server.arg(i)); 
			if (server.argName(i) == "mqttServer") config.mqttServer =   urldecode(server.arg(i));
			if (server.argName(i) == "deviceIdentifier") config.deviceIdentifier =    server.arg(i).toInt(); 
			if (server.argName(i) == "ip_0") if (checkRange(server.arg(i))) 	config.IP[0] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_1") if (checkRange(server.arg(i))) 	config.IP[1] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_2") if (checkRange(server.arg(i))) 	config.IP[2] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_3") if (checkRange(server.arg(i))) 	config.IP[3] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_0") if (checkRange(server.arg(i))) 	config.Netmask[0] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_1") if (checkRange(server.arg(i))) 	config.Netmask[1] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_2") if (checkRange(server.arg(i))) 	config.Netmask[2] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_3") if (checkRange(server.arg(i))) 	config.Netmask[3] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_0") if (checkRange(server.arg(i))) 	config.Gateway[0] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_1") if (checkRange(server.arg(i))) 	config.Gateway[1] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_2") if (checkRange(server.arg(i))) 	config.Gateway[2] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_3") if (checkRange(server.arg(i))) 	config.Gateway[3] =  server.arg(i).toInt();
			if (server.argName(i) == "dhcp") config.dhcp = true;
		}
		 server.send_P ( 200, "text/html", PAGE_WaitAndReload );
		WriteConfig();
		ConfigureWifi();
		AdminTimeOutCounter=0;
		
	}
	else
	{
		server.send_P ( 200, "text/html", PAGE_NetworkConfiguration ); 
	}
	Serial.println(__FUNCTION__); 
}



//
//   FILL THE PAGE WITH VALUES
//

void send_network_configuration_values_html()
{

	String values ="";

	values += "ssid|" + (String) config.ssid + "|input\n";
	values += "password|" +  (String) config.password + "|input\n";
	values += "ip_0|" +  (String) config.IP[0] + "|input\n";
	values += "ip_1|" +  (String) config.IP[1] + "|input\n";
	values += "ip_2|" +  (String) config.IP[2] + "|input\n";
	values += "ip_3|" +  (String) config.IP[3] + "|input\n";
	values += "nm_0|" +  (String) config.Netmask[0] + "|input\n";
	values += "nm_1|" +  (String) config.Netmask[1] + "|input\n";
	values += "nm_2|" +  (String) config.Netmask[2] + "|input\n";
	values += "nm_3|" +  (String) config.Netmask[3] + "|input\n";
	values += "gw_0|" +  (String) config.Gateway[0] + "|input\n";
	values += "gw_1|" +  (String) config.Gateway[1] + "|input\n";
	values += "gw_2|" +  (String) config.Gateway[2] + "|input\n";
	values += "gw_3|" +  (String) config.Gateway[3] + "|input\n";
	values += "dhcp|" +  (String) (config.dhcp ? "checked" : "") + "|chk\n";
	values += "mqttServer|" +  (String) config.mqttServer + "|input\n";
	values += "deviceIdentifier|" +  (String) config.deviceIdentifier + "|input\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}


//
//   FILL THE PAGE WITH NETWORKSTATE & NETWORKS
//

void send_connection_state_values_html()
{

	String state = "N/A";
	String Networks = "";
	if (WiFi.status() == 0) state = "Idle";
	else if (WiFi.status() == 1) state = "NO SSID AVAILBLE";
	else if (WiFi.status() == 2) state = "SCAN COMPLETED";
	else if (WiFi.status() == 3) state = "CONNECTED";
	else if (WiFi.status() == 4) state = "CONNECT FAILED";
	else if (WiFi.status() == 5) state = "CONNECTION LOST";
	else if (WiFi.status() == 6) state = "DISCONNECTED";



	 int n = WiFi.scanNetworks();
 
	 if (n == 0)
	 {
		 Networks = "<font color='#FF0000'>No networks found!</font>";
	 }
	else
    {
	 
		
		Networks = "Found " +String(n) + " Networks<br>";
		Networks += "<table border='0' cellspacing='0' cellpadding='3'>";
		Networks += "<tr bgcolor='#DDDDDD' ><td><strong>Name</strong></td><td><strong>Quality</strong></td><td><strong>Enc</strong></td><tr>";
		for (int i = 0; i < n; ++i)
		{
			int quality=0;
			if(WiFi.RSSI(i) <= -100)
			{
					quality = 0;
			}
			else if(WiFi.RSSI(i) >= -50)
			{
					quality = 100;
			}
			else
			{
				quality = 2 * (WiFi.RSSI(i) + 100);
			}


			Networks += "<tr><td><a href='javascript:selssid(\""  +  String(WiFi.SSID(i))  + "\")'>"  +  String(WiFi.SSID(i))  + "</a></td><td>" +  String(quality) + "%</td><td>" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")  + "</td></tr>";
		}
		Networks += "</table>";
	}
   
	String values ="";
	values += "connectionstate|" +  state + "|div\n";
	values += "networks|" +  Networks + "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}
