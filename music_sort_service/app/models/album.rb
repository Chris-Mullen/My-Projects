#  frozen_string_literal: true

# Album model definition
class Album < ApplicationRecord
  has_many :artists
  has_many :songs

  validates :title, presence: true, allow_blank: false
  validates :year, presence: true, allow_blank: false
end
