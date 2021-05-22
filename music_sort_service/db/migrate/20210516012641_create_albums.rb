#  frozen_string_literal: true

# Album migration definition
class CreateAlbums < ActiveRecord::Migration[6.1]
  def change
    create_table :albums, id: false do |t|
      t.string :uuid, limit: 36, primary: true, null: false
      t.string :title
      t.integer :year
      t.integer :tracks
      t.integer :disks, default: 1

      t.timestamps
    end
  end
end
