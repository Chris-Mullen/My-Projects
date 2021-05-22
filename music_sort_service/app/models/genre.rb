#  frozen_string_literal: true

# Genre model definition
class Genre < ApplicationRecord
  validates :title, presence: true, uniqueness: true, allow_blank: false
end
