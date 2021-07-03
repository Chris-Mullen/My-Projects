#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing artists
    class ArtistsController < ApplicationController
      def create
        artist = Artist.new(artist_params)
        unless artist.save
          render_json_validation_error(artist)
          return
        end

        render json: artist, status: :created
      end

      def show
        render json: Artist.where(uuid: params[:artist_id])
      end

      def show_all; end

      private

      def artist_params
        params.require(:artist).permit(:title)
      end
    end
  end
end
