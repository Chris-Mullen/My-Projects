class AlbumSerializer < ActiveModel::Serializer
  attributes :title, :songs, :artist, :year, :tracks, :disks
end
