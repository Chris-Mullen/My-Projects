#  frozen_string_literal: true

# Song model definition
class Song < ApplicationRecord
  belongs_to :album, optional: true

  validates :title, presence: true, allow_blank: false
  validates :path, presence: true, allow_blank: false
  validates :album_id, presence: true, allow_blank: false
  validates :genre_id, presence: true, allow_blank: false

  def self.create_song(params)
    album_id = Album.where(title: params[:album]).first.uuid
    unless album_id
      render_json_not_found_error('album', params[:album])
      return
    end

    genre_id = Genre.where(title: params[:genre]).first.uuid
    unless genre_id
      render_json_not_found_error('genre', params[:genre])
      return
    end

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
