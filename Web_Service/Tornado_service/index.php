<!DOCTYPE html>
<html>
<head>
	<title>Tornado Detector System</title>
</head>
<body>
    <?php include 'Service/database_handler.php'; 
    $fields = array();
    $params = array();
    $values = array();
    $arduino = select_data("tb_mst_arduino",$fields,$params,$values);
    ?>
    
	<center><img src="" width="100" height="100"></center>
		<h1 align="center">
			Input Data
		</h1>
	<div class="wrapper" align="center">
	<table>
		<form id="form_data"  action="Service/insert_from_form.php" method="POST">
			
		<tr>
			<td>Lokasi Arduino</td>
			<td> </td>
			<td>
			    <select name="id_arduino">
			        <?php foreach($arduino as $ard){ ?>
			            <option value="<?php echo $ard['id_arduino']?>"> <?php echo $ard['lokasi'] ?></option>
			        <?php }?>
			    </select>
			    
			    </td>
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