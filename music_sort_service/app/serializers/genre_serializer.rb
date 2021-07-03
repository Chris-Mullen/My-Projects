#  frozen_string_literal: true

# Genre serializer definition
class GenreSerializer < ActiveModel::Serializer
  attributes :uuid, :title, :songs

  def songs; end
end
