#  frozen_string_literal: true

# Genre serializer definition
class GenreSerializer < ActiveModel::Serializer
  attributes :title, :songs

  def songs; end
end
