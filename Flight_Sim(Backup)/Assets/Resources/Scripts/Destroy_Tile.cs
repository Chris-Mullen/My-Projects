using UnityEngine;
using System.Collections;

public class Destroy_Tile : MonoBehaviour {
	void OnTriggerStay(Collider coll){
		if (coll.gameObject.tag == "Tile"){
			Destroy(coll.gameObject);
			Destroy(this.gameObject);
		}
	}
}
