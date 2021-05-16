class CreateArtists < ActiveRecord::Migration[6.1]
  def change
    create_table :artists, id: :uuid do |t|
      t.String :title

      t.timestamps
    end
  end
end
