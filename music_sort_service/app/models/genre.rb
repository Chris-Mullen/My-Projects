class Genre < ApplicationRecord
  validates :title, presence: true, allow_blank: false
end
