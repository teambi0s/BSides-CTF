<!DOCTYPE html>
<html>
<head>
	<title>Auth3ntication</title>
	<script type="text/javascript" src="http://code.jquery.com/jquery-1.11.1.js"></script>

		
</head>
<body>
<h4>Auth3ntication
</h4>
<hr />

		<form action="#" method="post">
			<label>Username</label>
			<input class="form-control" type="text" name="username" id="cuser" placeholder="Username" />
			<label>Password</label>
			<input type="password" class="form-control" name="password" id="cpass" placeholder="Password" />
			<input type="submit" style="margin-top: 12px;" value="Login" class="form-control btn btn-success c_submit" />
		</form>
	<script type="text/javascript">
			$(".c_submit").click(function(event) {
				event.preventDefault();
				var u = $("#cpass").val();
				var k = $("#cuser").val();
				var func = "\x0d\x13\x45\x17\x48\x09\x5e\x4b\x17\x3c\x1a\x1f\x2b\x1b\x7a\x0c\x1f\x66\x0b\x1a\x3e\x51\x0b\x41\x11\x58\x17\x4d\x55\x16\x42\x01\x52\x4b\x0f\x5a\x07\x00\x00\x07\x06\x40\x4d\x07\x5a\x07\x14\x19\x0b\x07\x5a\x4d\x03\x47\x01\x13\x43\x0b\x06\x50\x06\x13\x7a\x02\x5d\x4f\x5d\x18\x09\x41\x42\x15\x59\x48\x4d\x4f\x59\x1d\x43\x10\x15\x00\x1a\x0e\x17\x05\x51\x0d\x1f\x1b\x08\x1a\x0e\x03\x1c\x5d\x0c\x05\x15\x59\x55\x09\x0d\x0b\x41\x0e\x0e\x5b\x10\x5b\x01\x0d\x0b\x55\x17\x02\x5a\x0a\x5b\x05\x10\x0d\x52\x43\x40\x15\x46\x4a\x1d\x5f\x4a\x14\x48\x4b\x40\x5f\x55\x10\x42\x15\x14\x06\x07\x46\x01\x55\x16\x42\x48\x10\x4b\x49\x16\x07\x07\x08\x11\x18\x5b\x0d\x18\x50\x46\x5c\x43\x0a\x1c\x59\x0f\x43\x17\x58\x11\x04\x14\x48\x57\x0f\x0a\x46\x17\x48\x4a\x07\x1a\x46\x0c\x19\x12\x5a\x22\x1f\x0d\x06\x53\x43\x1b\x54\x17\x06\x1a\x0d\x1a\x50\x43\x18\x5a\x16\x07\x14\x4c\x4a\x1d\x1e";
				buf = "";
				if(k.length == 9) {
					for(i = 0, j = 0; i < func.length; i++) {
						c = parseInt(func.charCodeAt(i));
						c = c ^ k.charCodeAt(j);
						if(++j == k.length) {
							j = 0;
						}
						buf += eval('"' + a(x(c)) + '"');
					}
					eval(buf);
					
				} else {
					$("#cresponse").html("<div class='alert alert-danger'>Invalid creds...</div>");
				}
			});
			
			function a(h) {
				if(h.length != 2) {
					h = "\x30" + h;
				}
				return "\x5c\x78" + h;
			}
			
			function x(d) {
				if(d < 0) {
					d = 0xFFFFFFFF + d + 1;
				}
				return d.toString(16).toUpperCase();
			}
	</script>
	
	<?php
$r = $_GET['p'];
if ($r=='XorIsNotSooS3cur3') {
	echo "flag{586f7249734e6f74536f6f533363757233}";
}

?>
	
		</div>
		<div id="cresponse">
		</div>
		
<hr />
</body>
</html>