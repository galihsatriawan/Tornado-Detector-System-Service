<!DOCTYPE html>
<html>
<head>
	<title>Tornado Detector System</title>
</head>
<body>
	<center><img src="" width="100" height="100"></center>
		<h1 align="center">
			Input Data
		</h1>
	<div class="wrapper" align="center">
	<table>
		<form id="form_data"  action="../insert_data.php" method="POST">
			
		<tr>
			<td>ID Arduino</td>
			<td> </td>
			<td><input type="number" name="id_arduino"></td>
		</tr>
		<tr>
			<td>Wind Speed</td>
			<td> </td>
			<td><input type="number" step="0.5" name="wind_speed"></td>
		</tr>
		<tr>
			<td>Note</td>
			<td> </td>
			<td><input type="text" name="note"></td>
		</tr>
		</form>
	</table>

	</div>
	<br>
	<center><button form="form_data" type="submit">Submit</button></center>
</body>
</html>