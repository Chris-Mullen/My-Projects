class CreateAlbums < ActiveRecord::Migration[6.1]
  def change
    create_table :albums, id: :uuid do |t|
      t.String :title
      t.references :artist, null: false, foreign_key: true, type: :uuid
      t.Integer :year
      t.Integer :total_tracks
      t.Integer :total_disks

      t.timestamps
    end
  end
end
