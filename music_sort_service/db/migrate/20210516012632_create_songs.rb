class CreateSongs < ActiveRecord::Migration[6.1]
  def change
    create_table :songs, id: :uuid do |t|
      t.String :title
      t.String :genre
      t.String :comments
      t.String :path
      t.references :album, null: false, foreign_key: true, type: :uuid
      t.Integer :track
      t.Integer :disk

      t.timestamps
    end
  end
end
