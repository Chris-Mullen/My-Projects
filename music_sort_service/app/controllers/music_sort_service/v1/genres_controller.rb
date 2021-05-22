#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing genres
    class GenresController < ApplicationController
      def create
        genre = Genre.new(genre_params)
        unless genre.save
          render_json_validation_error genre
          return
        end

        render json: genre, status: :created
      end

      def show; end

      private

      def genre_params
        params.require(:genre).permit(:title)
      end
    end
  end
end
