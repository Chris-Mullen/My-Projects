class CreateAlbums < ActiveRecord::Migration[6.1]
  def change
    create_table :albums, id: false do |t|
      t.string :uuid, limit: 36, primary: true, null: false
      t.string :title
      t.string :artist_id, null: false, foreign_key: true, index: true
      t.integer :year
      t.integer :total_tracks
      t.integer :total_disks, default: 1

      t.timestamps
    end
  end
end
