#  frozen_string_literal: true

# Artist model definition
class Artist < ApplicationRecord
  belongs_to :album, optional: true

  validates :title, presence: true, uniqueness: true, allow_blank: false
end
