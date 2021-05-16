class Album < ApplicationRecord
  belongs_to :artist

  validates :title, presence: true, allow_blank: false
  validates :artist, presence: true, allow_blank: false
  validates :year, presence: true, allow_blank: false
end
