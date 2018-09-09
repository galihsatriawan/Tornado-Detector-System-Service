<!DOCTYPE html>
<html>
<head>
	<title>Tornado Detector System</title>
</head>
<body>
    <?php include '../Service/database_handler.php'; 
    $fields = array();
    $params = array();
    $values = array();
    $arduino = select_data("tb_mst_arduino",$fields,$params,$values);
    ?>
    
	<center><img src="" width="100" height="100"></center>
		<h1 align="center">
			Input Data Arduino
		</h1>
	<div class="wrapper" align="center">
	<table>
		<form id="form_data"  action="../Service/insert_arduino.php" method="POST">
			
		<tr>
			<td>Nama Arduino</td>
			<td> </td>
			<td><input type="text" name="name"></td>
		</tr>
		<tr>
			<td>Lokasi Arduino</td>
			<td> </td>
			<td><input type="text" name="location"></td>
		</tr>
		<tr>
			<td>Altitude Lokasi</td>
			<td> </td>
			<td><input type="number" step="0.5" name="altitude"></td>
		</tr>
		<tr>
			<td>Longtitude Lokasi</td>
			<td> </td>
			<td><input type="number" step="0.5" name="longtitude"></td>
		</tr>
		
		</form>
	</table>

	</div>
	<br>
	<center><button form="form_data" type="submit">Submit</button></center>
</body>
</html>