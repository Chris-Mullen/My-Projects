#  frozen_string_literal: true

# Song migration definition
class CreateSongs < ActiveRecord::Migration[6.1]
  def change
    create_table :songs, id: false do |t|
      t.string :uuid, limit: 36, primary: true, null: false
      t.string :title
      t.string :comments
      t.string :path
      t.string :album_id, null: false, foreign_key: true, index: true
      t.string :genre_id, null: false, foreign_key: true, index: true
      t.integer :track
      t.integer :disk, default: 1

      t.timestamps
    end
  end
end
