#  frozen_string_literal: true

# Song model definition
class Song < ApplicationRecord
  belongs_to :album, optional: true

  validates :title, presence: true, allow_blank: false
  validates :path, presence: true, allow_blank: false
  validates :album_id, presence: true, allow_blank: false
  validates :genre_id, presence: true, allow_blank: false

  def self.create_song(params, genre_id, album_id)
    song = Song.new(
      {
        title: params[:title],
        track: params[:track],
        disk: params[:disk],
        comments: params[:comments],
        path: params[:path],
        album_id: album_id,
        genre_id: genre_id
      }
    )
  end
end
