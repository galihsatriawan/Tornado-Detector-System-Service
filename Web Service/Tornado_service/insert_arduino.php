
<?php
include 'database_handler.php';
if($_SERVER['REQUEST_METHOD'] == 'POST'){
// if(true){
	
	$respon = array();
	 
	$name = $_POST['name'];
	$location = $_POST['location'];
	$altitude = $_POST['altitude'];
	$longtitude = $_POST['longtitude'];
	// $token= "oke";
	$fields = array("name","location","altitude","longtitude");
	$values = array($name,$location,$altitude,$longtitude);
	insert_data("tb_mst_arduino",$fields,$values);
	$respon['Pesan']= "Berhasil"." ".$token;
	echo json_encode($respon);
	
}else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
}
?>