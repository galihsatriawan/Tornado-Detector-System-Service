
<?php
include 'database_handler.php';

// echo "$date";
if($_SERVER['REQUEST_METHOD'] == 'POST'){
// if(true){
	$var_1 = $_POST['wind_speed'];
	// $var_1 = 3.0;
	// $id = "test";
	$id = $_POST['id_arduino'];
	$date = date("Y-m-d H:m:s");
	$note = $_POST['note'];
	if($var_1>45){
		// Send Notif
		$send = "send";
		include 'send_notif.php';
	}
	// $token= "oke";
	$fields = array("var_1","id_arduino","tgl_data");
	$values = array($var_1,$id,$date);
	insert_data("tb_mst_data",$fields,$values);
	$respon['Pesan']= "Berhasil"." ".$id;
	echo json_encode($respon);
	
}else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
}
?>