class Song < ApplicationRecord
  belongs_to :album

  validates :title, presence: true, allow_blank: false
  validates :path, presence: true, allow_blank: false
  validates :album, presence: true, allow_blank: false
  validates :genre, presence: true, allow_blank: false
end
