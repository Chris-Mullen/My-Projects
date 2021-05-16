class CreateSongs < ActiveRecord::Migration[6.1]
  def change
    create_table :songs, id: :uuid do |t|
      t.String :title
      t.String :comments
      t.String :path
      t.references :album, null: false, foreign_key: true, type: :uuid
      t.references :genre, null: false, foreign_key: true, type: :uuid
      t.Integer :track
      t.Integer :disk, default: 1

      t.timestamps
    end
  end
end
