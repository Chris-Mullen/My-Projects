#  frozen_string_literal: true

# Artist serializer definition
class ArtistSerializer < ActiveModel::Serializer
  attributes :title, :albums
end
