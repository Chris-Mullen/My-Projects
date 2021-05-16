class CreateGenres < ActiveRecord::Migration[6.1]
  def change
    create_table :genres, id: :uuid do |t|
      t.String :title

      t.timestamps
    end
  end
end
