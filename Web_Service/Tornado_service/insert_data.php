
<?php
include 'database_handler.php';

// echo "$date";
// $fields = array();
// 		$params = array();
// 		$values = array();
// $arduino = select_data("tb_mst_arduino",$fields,array("id_arduino"),array(2));
// echo $arduino[0]['lokasi'];
if($_SERVER['REQUEST_METHOD'] == 'POST'){
// if(true){
	$var_1 = $_POST['wind_speed'];
	// $var_1 = 3.0;
	// $id = "test";
	$id = $_POST['id_arduino'];
	$date = date("Y-m-d H:m:s");
	// What do we send for
	$note = $_POST['note'];
	if($var_1>=90){
		// Send Notif
		$send = "send";
		$fields = array();
		$params = array();
		$values = array();
		$query = select_data("tb_mst_token",$fields,$params,$values);
		$arduino = select_data("tb_mst_arduino",$fields,array("id_arduino"),array($id));
		// include 'send_notif.php';
		$title = "Note :";
		$body =$note." , ".$arduino[0]['lokasi'];
// if(true){
	
	// $query = mysqli_query($con,$sql);
	
	// print_r($query);
	$result = array();
	// $hasil = mysqli_fetch_all($query);
	foreach ($query as $key => $value) {
		# code...
		// print_r($key);
		// print_r($value);
		$result[]= $value['token'];
	}
	$token_tujuan =$result;

		define('API_ACCESS_KEY','AAAAFawvTf8:APA91bFHNepdyK2XhXBDM4D_5s8fQ3kA8TFFd2nvh2FuCmgIE3sDyW0UzEpQIrHr0VFxE2N9SKQqsEIj9JvYlDgNOQAr7KVuNkpCPh1QhVhySfqX0dlHVGr3Oi1QOaSDbnqLX49FlhmFpnhYkQH_kUl1SQMUseuHVg');
		$url = 'https://fcm.googleapis.com/fcm/send';
		//$registrationIds = array($_GET['id']);
		$registrationIds =$token_tujuan;
		// prepare the message
		$message = array( 
		  'title'     => $title,
		  'body'      => $body
		);
		$fields = array( 
		  'registration_ids' => $registrationIds, 
		  // 'data'             => $message  --> Wrong written
		  'data'             => $message
		);
		$headers = array( 
		  'Authorization: key='.API_ACCESS_KEY, 
		  'Content-Type: application/json'
		);
		$ch = curl_init();
		curl_setopt( $ch,CURLOPT_URL,$url);
		curl_setopt( $ch,CURLOPT_POST,true);
		curl_setopt( $ch,CURLOPT_HTTPHEADER,$headers);
		curl_setopt( $ch,CURLOPT_RETURNTRANSFER,true);
		curl_setopt( $ch,CURLOPT_SSL_VERIFYPEER,false);
		curl_setopt( $ch,CURLOPT_POSTFIELDS,json_encode($fields));
		$result = curl_exec($ch);
		curl_close($ch);

		//$respon['Pesan'] = "Good ".$con->error;
		//$respon['id_arduino'] = 1;
		//echo json_encode($respon);
		
	}
	// $token= "oke";
	if($var_1>=311){
		$indication = "F5";
	}else if($var_1>=266){
		$indication = "F4";
	}else if($var_1>=221){
		$indication = "F3";
	}else if($var_1>=176){
		$indication = "F2";
	}else if($var_1>=131){
		$indication = "F1";
	}else if($var_1>=90){
		$indication = "F0";
	}else{
		$indication = "Normal";
	}
	$fields = array("var_1","id_arduino","tgl_data","indication");
	$values = array($var_1,$id,$date,$indication);
	insert_data("tb_mst_data",$fields,$values);
	$respon['Pesan']= "Berhasil"." ".$id;
	echo json_encode($respon);
	header("Location: /View/Input_data.php");
}else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
}
?>