class CreateArtists < ActiveRecord::Migration[6.1]
  def change
    create_table :artists, id: false do |t|
      t.string :uuid, limit: 36, primary: true, null: false
      t.string :title

      t.timestamps
    end
  end
end
