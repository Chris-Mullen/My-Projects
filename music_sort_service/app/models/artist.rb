#  frozen_string_literal: true

# Artist model definition
class Artist < ApplicationRecord
  validates :title, presence: true, allow_blank: false
end
