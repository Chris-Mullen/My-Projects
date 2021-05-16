#  frozen_string_literal: true

# Song serializer definition
class SongSerializer < ActiveModel::Serializer
  attributes :id, :title, :comments, :path, :artist, :album, :genre, :track, :disk
end
