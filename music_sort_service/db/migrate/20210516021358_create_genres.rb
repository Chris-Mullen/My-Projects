#  frozen_string_literal: true

# Genre migration definition
class CreateGenres < ActiveRecord::Migration[6.1]
  def change
    create_table :genres, id: false do |t|
      t.string :uuid, limit: 36, primary: true, null: false
      t.string :title, unique: true

      t.timestamps
    end
  end
end
