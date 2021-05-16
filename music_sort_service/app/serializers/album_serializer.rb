#  frozen_string_literal: true

# Album serializer definition
class AlbumSerializer < ActiveModel::Serializer
  attributes :title, :songs, :artist, :year, :tracks, :disks
end
