using UnityEngine;
using System.Collections;
using System.Collections.Generic;//For Queue Structure

public class Spawn_Tile : MonoBehaviour {

	private GameObject target;
	private GameObject newtile;
	private bool contains=false;
	private Queue<GameObject> created = new Queue<GameObject>();//9 tiles total will be stored at a time
	private int maxtiles=15;
	public float mapsize=100.0f;

	void Start(){
		Spawn(Vector3.zero);//store origin as our first tile
		}

	void OnTriggerEnter(Collider coll){
		target = coll.GetComponent<Collider>().transform.parent.gameObject;
		if (coll.gameObject.name == "Trigger_0") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x,0,coll.gameObject.transform.parent.parent.position.z+mapsize));
		}
		if (coll.gameObject.name == "Trigger_1") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x+mapsize,0,coll.gameObject.transform.parent.parent.position.z+mapsize));
		}
		if (coll.gameObject.name == "Trigger_2") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x+mapsize,0,coll.gameObject.transform.parent.parent.position.z));
		}
		if (coll.gameObject.name == "Trigger_3") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x+mapsize,0,coll.gameObject.transform.parent.parent.position.z-mapsize));
		}
		if (coll.gameObject.name == "Trigger_4") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x,0,coll.gameObject.transform.parent.parent.position.z-mapsize));
		}
		if (coll.gameObject.name == "Trigger_5") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x-mapsize,0,coll.gameObject.transform.parent.parent.position.z-mapsize));
		}
		if (coll.gameObject.name == "Trigger_6") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x-mapsize,0,coll.gameObject.transform.parent.parent.position.z));
		}
		if (coll.gameObject.name == "Trigger_7") {
			Spawn(new Vector3(coll.gameObject.transform.parent.parent.position.x-mapsize,0,coll.gameObject.transform.parent.parent.position.z+mapsize));
		}
	}
	void Spawn(Vector3 position){
		foreach (GameObject element in created) {
			if(element.transform.position==position){
				contains=true;
				break;
			}
			else{
				contains=false;
			}
		}
		if (contains==false) {
			newtile = Instantiate (Resources.Load ("Prefabs/Map_Section_1"), position, Quaternion.identity) as GameObject;
			created.Enqueue (newtile);
		}
		if (created.Count > maxtiles) {
			//delete_old(created.Dequeue ());
			//newtiledestroyer=Instantiate (Resources.Load ("Prefabs/Tile_Destroyer"), created.Dequeue (), Quaternion.identity) as GameObject;
			Destroy (created.Dequeue());
		}
	}

	void delete_old(Vector3 center) {
		float radius = 1.0f;
		Collider[] hitColliders = Physics.OverlapSphere(center, radius);
		for(int i=0;i<hitColliders.Length;i++) {
			Destroy(hitColliders[i]);
		}
	}
}