using UnityEngine;
using System.Collections;

public class Startup : MonoBehaviour {

	private GameObject gameObject=null;

	void Start(){
		Spawn_Tile (Vector3.zero);
		}

	void Spawn_Tile(Vector3 position){
		gameObject=Instantiate(Resources.Load("Prefabs/Map_Section_1"),position,Quaternion.identity) as GameObject;
	}
}
